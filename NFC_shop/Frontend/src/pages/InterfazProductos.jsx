import { Link } from "react-router-dom";

export default function InterfazProductos() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Interfaz de Productos</h1>

      <p>Muestra los productos disponibles y sus números asociados.</p>

      <Link to="/buscar"><button>Ir a Búsqueda</button></Link>
      <Link to="/caja"><button>Ir a Caja Registradora</button></Link>
      <Link to="/almacen"><button>Ir al Almacén</button></Link>
    </div>
  );
}