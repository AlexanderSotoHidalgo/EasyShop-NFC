import { Link } from "react-router-dom";
import "../styles/pantallaFinal.css";

export default function PantallaFinal() {
  return (
    <div className="confirm-wrapper">

      {/* BOTÓN CERRAR (ROJO) */}
      <Link to="/" className="cerrar-btn">❌</Link>

      {/* TARJETA CENTRAL */}
      <div className="confirm-card">

        {/* ICONO CHECK */}
        <div className="icon-check">✔️</div>

        {/* MENSAJES */}
        <h1 className="titulo">¡Gracias por tu compra!</h1>
        <p className="subtitulo">
          Tu solicitud de compra ha sido recibida
        </p>
        <p className="codigo">
          Pedido: OV001-0000000001
        </p>

        {/* CUADRO DE INFORMACIÓN */}
        <div className="info-box">
          
          {/* Resumen */}
          <div className="columna">
            <h3>Resumen de Compra</h3>

            <p>2 x Plátanos Maduros</p>
            <p>1 x Pan Integral</p>
            <p>1 x Leche Entera 1L</p>
          </div>

          {/* Medio de pago */}
          <div className="columna">
            <h3>Medio de Pago</h3>

            <p>Número de Tarjeta</p>
            <p>XXXX XXXX XXXX 1111</p>
          </div>

          {/* Totales */}
          <div className="columna totales">
            <p>Total sin IGV: S/ 5.35</p>
            <p>Total de Impuestos: S/ 3.00</p>

            <h2 className="total-final">Total: S/ 8.35</h2>
          </div>

        </div>
      </div>
    </div>
  );
}
