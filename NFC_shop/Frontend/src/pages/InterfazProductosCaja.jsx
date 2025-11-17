import { Link } from "react-router-dom";
import "../styles/InterfazProductosCaja.css";

export default function InterfazProductosCaja() {
  const productos = [
    { nombre: "Manzanas Rojas", precio: 2.99, icono: "🍎", numero: 1 },
    { nombre: "Plátanos Maduros", precio: 1.50, icono: "🍌", numero: 2 },
    { nombre: "Pan Integral", precio: 3.25, icono: "🍞", numero: 3 },
    { nombre: "Leche Entera 1L", precio: 2.10, icono: "🥛", numero: 4 },
    { nombre: "Huevos Grade A", precio: 4.75, icono: "🥚", numero: 5 },
    { nombre: "Pechuga Pollo", precio: 8.99, icono: "🍗", numero: 6 },
    { nombre: "Arroz Blanco 1kg", precio: 1.99, icono: "🍚", numero: 7 },
  ];

  return (
    <div className="ipc-wrapper">

      {/* TOP BAR */}
      <div className="ipc-topbar">
        <Link to="/caja" className="back-btn">⬅</Link>
        Productos
        <div className="ipc-icon">📄</div>
      </div>

      {/* CONTENIDO GENERAL */}
      <div className="ipc-content">

        {/* LISTA IZQUIERDA */}
        <div className="ipc-lista">
          <div className="ipc-title">Productos</div>

          <div className="ipc-lista-cards">
            {productos.map((p, index) => (
              <div className="ipc-item" key={index}>
                
                {/* Emoji */}
                <div className="ipc-icono">{p.icono}</div>

                {/* Info */}
                <div className="ipc-info">
                  <p className="ipc-nombre">{p.nombre}</p>
                  <p className="ipc-precio">S/ {p.precio.toFixed(2)}</p>
                </div>

                {/* Número asignado */}
                <div className="ipc-num">{p.numero}</div>
              </div>
            ))}
          </div>

        </div>

        {/* LADO DERECHO | IMAGEN + TEXTO */}
        <div className="ipc-info-right">
          <div className="ipc-bombilla">💡</div>

          <p className="ipc-texto">
            Los números asignados los puedes presionar al comprar para que los productos que los tengan asignados sean agregados automáticamente al carrito.
          </p>
        </div>
      </div>
    </div>
  );
}
