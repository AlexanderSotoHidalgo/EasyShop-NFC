from pathlib import Path

def contar_archivos_pathlib(directorio):
    return sum(1 for archivo in Path(directorio).rglob('*') if archivo.is_file())

# Ejemplo de uso:
directorio = r'C:\ruta\de\tu\directorio'
print(f"Número total de archivos: {contar_archivos_pathlib(directorio)}")
