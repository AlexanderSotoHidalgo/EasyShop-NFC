import { Link } from "react-router-dom";

export default function ResumenCompra() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Resumen de Compra</h1>

      <p>Lista de artículos escaneados, clara y accesible.</p>

      <Link to="/confirmar"><button>Confirmar Venta</button></Link>
      <Link to="/caja"><button>Volver a Caja</button></Link>
    </div>
  );
}
