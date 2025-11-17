import { Link } from "react-router-dom";
import "../styles/ConfirmarVenta.css";

export default function ConfirmarVenta() {
  
  const carrito = [
    { nombre: "Plátanos Maduros", categoria: "Frutas", precio: 1.50, icono: "🍌" },
    { nombre: "Plátanos Maduros", categoria: "Frutas", precio: 1.50, icono: "🍌" },
    { nombre: "Pan Integral", categoria: "Panadería", precio: 3.25, icono: "🍞" },
    { nombre: "Leche Entera 1L", categoria: "Lácteos", precio: 2.10, icono: "🥛" },
  ];

  const total = carrito.reduce((acc, p) => acc + p.precio, 0);
  
  return (
    <div className="confirmar-container">

      {/* --- Barra superior --- */}
      <div className="confirmar-topbar">
        🧾 Venta en Curso
      </div>

      {/* --- Caja principal --- */}
      <div className="confirmar-box">

        {/* Total */}
        <div className="confirmar-total">
          <h2>S/ {total.toFixed(2)}</h2>
          <p>{carrito.length} productos</p>
        </div>

        {/* Lista de productos */}
        <div className="confirmar-lista">
          {carrito.map((p, i) => (
            <div className="confirmar-item" key={i}>
              <div className="item-icon">{p.icono}</div>
              <div className="item-info">
                <p className="item-nombre">{p.nombre}</p>
                <p className="item-categoria">{p.categoria}</p>
              </div>
              <div className="item-precio">
                S/ {p.precio.toFixed(2)}
              </div>
            </div>
          ))}
        </div>
      </div>

      {/* --- Botones inferiores --- */}
      <div className="confirmar-botones">
        <button className="btn-vaciar">⛔ Vaciar (Esc)</button>
        <button className="btn-deshacer">↩ Deshacer (Del)</button>

        {/* 🔵 El botón que te interesa */}
        <Link to="/final" className="btn-finalizar">
          🟩 Finalizar Venta (Enter)
        </Link>

        {/* Volver */}
        <Link to="/caja" className="volver-link">Volver</Link>
      </div>

    </div>
  );
}
