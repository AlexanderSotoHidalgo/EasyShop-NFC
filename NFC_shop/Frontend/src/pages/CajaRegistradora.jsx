import { Link } from "react-router-dom";
import "../styles/CajaRegistradora.css";

export default function CajaRegistradora() {
  return (
    <div className="caja-wrapper">

      {/* Barra superior */}
      <div className="caja-topbar">
        <Link to="http://localhost:5173/" className="back-btn">⬅</Link>
        Caja Registradora
        <div className="icons-top">
          📄  🔔
        </div>
      </div>

      <div className="caja-layout">

        {/* PANEL IZQUIERDO */}
        <div className="caja-left">

          {/* Selección rápida */}
          <div className="panel-card">
            <div className="panel-title">Controles Principales</div>
            
            <div className="panel-item highlight">
              <span>⚡ Selección Rápida</span>
            </div>

            <div className="sub-panel">
              <p className="sub-item">1️⃣ Escanear producto</p>
              <p className="sub-item">2️⃣ Añadir venta</p>
              <p className="sub-item">3️⃣ Remover ítems</p>
              <p className="sub-item">4️⃣ Selección rápida</p>
              <p className="sub-item">5️⃣ Venta corta</p>
            </div>
          </div>

          {/* Resumen actual */}
          <div className="panel-card footer-card">
            <div className="panel-title">📘 Resumen Actual</div>

            <div className="summary-row">
              <span>Productos:</span>
              <span>0</span>
            </div>

            <div className="summary-row">
              <span>Total:</span>
              <span className="summary-total">S/ 0.00</span>
            </div>
          </div>
        </div>

        {/* PANEL CENTRAL */}
        <div className="caja-center">

          <div className="venta-header">
            <div>
              <div className="text-small">CARRITO ACTIVO</div>
              <div className="venta-title">Venta en Curso</div>
            </div>

            <div className="venta-total">
              <span>S/ 0.00</span>
              <span className="sub">0 productos</span>
            </div>
          </div>

          {/* CARRITO VACÍO */}
          <div className="carrito-vacio">
            <div className="carrito-icon">🛒</div>
            <p className="carrito-title">Carrito Vacío</p>
            <p className="carrito-sub">Usa las teclas 1-5 para escanear productos<br/>o presiona la opción "Selección Rápida"</p>
          </div>

          {/* BOTONES PRINCIPALES */}
          <div className="action-buttons">
            <button className="btn rojo">Vacíar (Esc)</button>
            <button className="btn amarillo">⟲ Deshacer (Del)</button>
            <Link to="/resumen" className="btn verde link-btn">
            Finalizar Venta (Enter)
            </Link>
            <Link to="/productos-caja" className="btn naranja">
            ⚡ Selección Rápida
            </Link>
          </div>

        </div>

      </div>
    </div>
  );
}
