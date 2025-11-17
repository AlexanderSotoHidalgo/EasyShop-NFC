import { Link } from "react-router-dom";

export default function BusquedaProductos() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Búsqueda de Productos</h1>

      <p>Busca productos por nombre, siempre y cuando existan.</p>

      <Link to="/"><button>Volver</button></Link>
      <Link to="/caja"><button>Ir a Caja Registradora</button></Link>
    </div>
  );
}