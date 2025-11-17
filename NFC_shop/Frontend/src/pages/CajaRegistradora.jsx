import { Link } from "react-router-dom";

export default function CajaRegistradora() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Caja Registradora</h1>

      <p>Muestra productos seleccionados y el total a pagar.</p>

      <Link to="/resumen"><button>Ir al Resumen de Compra</button></Link>
      <Link to="/"><button>Volver a Productos</button></Link>
    </div>
  );
}
