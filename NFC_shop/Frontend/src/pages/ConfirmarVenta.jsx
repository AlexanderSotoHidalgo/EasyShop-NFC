import { Link } from "react-router-dom";

export default function ConfirmarVenta() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Confirmar Venta</h1>

      <p>Pantalla final para confirmar o cancelar la compra.</p>

      <Link to="/"><button>Volver al inicio</button></Link>
    </div>
  );
}
