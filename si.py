import random
import os
import time

# Lista de números rojos y negros según la ruleta europea
NUMEROS_ROJOS = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}
NUMEROS_NEGROS = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35}

# Función para girar la ruleta
def girar_ruleta():
    numero = random.randint(0, 36)
    if numero in NUMEROS_ROJOS:
        color = "rojo"
    elif numero in NUMEROS_NEGROS:
        color = "negro"
    else:
        color = "verde"  # Para el 0
    par_impar = "par" if numero % 2 == 0 and numero != 0 else "impar" if numero != 0 else "ninguno"
    return numero, color, par_impar

# Función para validar entradas numéricas
def obtener_entero(mensaje, minimo=1, maximo=None):
    while True:
        entrada = input(mensaje)
        if entrada.lower() == "salir":
            return "salir"
        if entrada.isdigit():
            numero = int(entrada)
            if (minimo is None or numero >= minimo) and (maximo is None or numero <= maximo):
                return numero
            else:
                if maximo:
                    print(f"Por favor, introduce un número entre {minimo} y {maximo}.")
                else:
                    print(f"Por favor, introduce un número mayor o igual a {minimo}.")
        else:
            print("Por favor, introduce un número válido.")

# Función para mostrar y eliminar las reglas
def mostrar_reglas():
    print("\nREGLAS DEL JUEGO:")
    print("- Comienzas con 100 soles.")
    print("- Debes alcanzar 250 soles para ganar.")
    print("- Si te quedas sin dinero, pierdes.")
    print("- Puedes apostar en número exacto, color (rojo/negro), par/impar o docenas.")
    print("- El pago varía según la apuesta:")
    print("  * Número exacto: 35 a 1")
    print("  * Color (rojo/negro): 1 a 1")
    print("  * Par/Impar: 1 a 1")
    print("  * Docenas: 2 a 1")
    print("- Puedes salir del juego en cualquier momento eligiendo 'salir' al seleccionar el tipo de apuesta.")
    print("\nPresiona Enter para continuar...")
    input()  # Espera indefinida hasta que el usuario presione Enter
    os.system('clear' if os.name == 'posix' else 'cls')

# Función para realizar una apuesta
def apostar(tipo, cantidad, saldo):
    if tipo == "numero":
        numero = obtener_entero("Apuesta a un número (0-36): ", 0, 36)
        if numero == "salir":
            return "salir", saldo, None
        return "continuar", saldo - cantidad, ("numero", numero)
    
    elif tipo == "color":
        color = ""
        while True:
            color = input("Apuesta a un color (rojo/negro): ").lower()
            if color in ["rojo", "negro"]:
                break
            else:
                print("Por favor, elige 'rojo' o 'negro'.")
        return "continuar", saldo - cantidad, ("color", color)
    
    elif tipo == "par_impar":
        eleccion = ""
        while True:
            eleccion = input("Apuesta a par o impar: ").lower()
            if eleccion in ["par", "impar"]:
                break
            else:
                print("Por favor, elige 'par' o 'impar'.")
        return "continuar", saldo - cantidad, ("par_impar", eleccion)
    
    elif tipo == "docena":
        docena = obtener_entero("Apuesta a una docena (1, 2 o 3): ", 1, 3)
        if docena == "salir":
            return "salir", saldo, None
        return "continuar", saldo - cantidad, ("docena", docena)
    
    else:
        print("Tipo de apuesta no válida.")
        return "continuar", saldo, None

# Función para manejar el flujo del juego
def jugar_ruleta():
    mostrar_reglas()  # Mostrar las reglas antes de comenzar
    saldo = 100  # Empiezas con 100 soles

    while saldo > 0 and saldo < 250:
        print(f"\nSaldo actual: {saldo} soles")

        # Asegurar que el tipo de apuesta sea válido
        while True:
            tipo_apuesta = input("Elige tu tipo de apuesta (numero/color/par_impar/docena) o 'salir' para terminar: ").lower()
            if tipo_apuesta in ["numero", "color", "par_impar", "docena", "salir"]:
                break
            else:
                print("Por favor, elige una opción válida: numero, color, par_impar, docena o salir.")

        if tipo_apuesta == "salir":
            print("Has decidido salir del juego. ¡Gracias por jugar!")
            break

        # Asegurar que la cantidad apostada sea válida
        while True:
            cantidad = obtener_entero(f"¿Cuánto deseas apostar? (Saldo disponible: {saldo} soles): ", 1, saldo)
            if cantidad == "salir":
                print("Has decidido salir del juego. ¡Gracias por jugar!")
                return
            else:
                break

        # Realizar la apuesta (sin girar la ruleta aún)
        estado, saldo, apuesta = apostar(tipo_apuesta, cantidad, saldo)
        if estado == "salir":
            print("Has decidido salir del juego. ¡Gracias por jugar!")
            break

        # Girar la ruleta DESPUÉS de la apuesta
        numero_ganador, color_ganador, par_impar_ganador = girar_ruleta()

        # Mostrar el resultado de la ruleta
        if numero_ganador == 0:
            print(f"Ruleta girando... El número es {numero_ganador} (verde)")
        else:
            print(f"Ruleta girando... El número es {numero_ganador} ({color_ganador}, {par_impar_ganador})")

        # Determinar si la apuesta fue ganadora
        if apuesta:
            tipo, valor = apuesta
            if tipo == "numero":
                if valor == numero_ganador:
                    ganancia = cantidad * 35  # Pago de 35 a 1 en número exacto
                    print(f"¡Correcto! Has ganado {ganancia} soles.")
                else:
                    ganancia = 0
                    print(f"Incorrecto. Has perdido {cantidad} soles.")

            elif tipo == "color":
                if valor == color_ganador:
                    ganancia = cantidad  # Pago de 1 a 1
                    print(f"¡Correcto! Has ganado {ganancia} soles.")
                else:
                    ganancia = 0
                    print(f"Incorrecto. Has perdido {cantidad} soles.")

            elif tipo == "par_impar":
                if valor == par_impar_ganador:
                    ganancia = cantidad  # Pago de 1 a 1
                    print(f"¡Correcto! Has ganado {ganancia} soles.")
                else:
                    ganancia = 0
                    print(f"Incorrecto. Has perdido {cantidad} soles.")

            elif tipo == "docena":
                docena_ganadora = ((numero_ganador - 1) // 12) + 1 if numero_ganador != 0 else None
                if docena_ganadora == valor:
                    ganancia = cantidad * 2  # Pago de 2 a 1
                    print(f"¡Correcto! Has ganado {ganancia} soles.")
                else:
                    ganancia = 0
                    print(f"Incorrecto. Has perdido {cantidad} soles.")

            saldo += ganancia

        if saldo >= 250:
            print("¡Felicidades! Has ganado el juego al alcanzar 250 soles.")
            break
        elif saldo <= 0:
            print("Lo siento, te has quedado sin dinero. ¡Fin del juego!")
            break

        # Espera de 10 segundos entre los giros
        print("Esperando 10 segundos para el próximo giro...")
        time.sleep(10)

# Iniciar el juego
if __name__ == "__main__":
    jugar_ruleta()
