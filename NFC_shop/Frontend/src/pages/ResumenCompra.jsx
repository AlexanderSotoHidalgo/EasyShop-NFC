import { Link } from "react-router-dom";
import "../styles/ResumenCompra.css";

export default function ResumenCompra() {

  const items = [
    { nombre: "Manzanas Rojas", cantidad: 2, precio: 2.99, icono: "🍎" },
    { nombre: "Pan Integral", cantidad: 1, precio: 3.25, icono: "🍞" },
    { nombre: "Huevos Grade A", cantidad: 1, precio: 4.75, icono: "🥚" },
  ];

  return (
    <div className="resumen-wrapper">

      {/* TOP BAR */}
      <div className="resumen-topbar">
        <Link to="/caja" className="back-btn">⬅</Link>
        Resumen de Compra
        <div className="icon-right">🧾</div>
      </div>

      {/* CARD PRINCIPAL */}
      <div className="resumen-card">

        <h2 className="resumen-title">🛒 Resumen de tu Compra</h2>

        <div className="resumen-lista">

          {items.map((item, i) => (
            <div className="resumen-item" key={i}>
              
              <div className="resumen-emoji">{item.icono}</div>

              <div className="resumen-info">
                <p className="resumen-nombre">{item.nombre}</p>
                <p className="resumen-detalle">
                  {item.cantidad} x S/ {item.precio.toFixed(2)}
                </p>
              </div>

              <p className="resumen-total-item">
                S/ {(item.cantidad * item.precio).toFixed(2)}
              </p>

            </div>
          ))}

        </div>

        {/* TOTALES */}
        <div className="resumen-totales">

          <div className="fila-total">
            <span>Subtotal:</span>
            <span>S/ 11.99</span>
          </div>

          <div className="fila-total">
            <span>Impuestos:</span>
            <span>S/ 1.40</span>
          </div>

          <div className="fila-total total-final">
            <span>Total a Pagar:</span>
            <span>S/ 13.39</span>
          </div>

        </div>

        {/* BOTONES */}
        <div className="resumen-buttons">
          <Link to="/caja">
            <button className="btn-volver">⬅ Volver</button>
          </Link>

          <Link to="/final">
            <button className="btn-finalizar">Finalizar Compra ✔</button>
          </Link>
        </div>

      </div>
    </div>
  );
}

