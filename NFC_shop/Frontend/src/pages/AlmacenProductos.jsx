import { Link } from "react-router-dom";

export default function AlmacenProductos() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Almacén de Productos</h1>

      <p>Muestra el stock disponible en la tienda.</p>

      <Link to="/"><button>Volver a Productos</button></Link>
    </div>
  );
}
