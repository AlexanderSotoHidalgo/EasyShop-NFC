import { Link } from "react-router-dom";

export default function AlmacenProductos() {
  const productos = [
    {
      nombre: "Manzanas",
      categoria: "Frutas",
      stock: 50,
      precio: 2.99,
      vencimiento: "20 días",
      icono: "🍎"
    },
    {
      nombre: "Leche",
      categoria: "Lácteos",
      stock: 25,
      precio: 1.99,
      vencimiento: "6 días",
      icono: "🥛"
    },
    {
      nombre: "Pan",
      categoria: "Panadería",
      stock: 15,
      precio: 1.49,
      vencimiento: "1 día",
      icono: "🍞"
    }
  ];

  return (
    <div style={{ fontFamily: "Arial, sans-serif", background: "#f3f6ff", height: "100vh" }}>
      
      {/* ----- TOP BAR ----- */}
      <div style={{
        background: "#1a73e8",
        padding: "15px",
        color: "white",
        fontSize: "20px",
        fontWeight: "bold",
        display: "flex",
        alignItems: "center",
      }}>
        ☰ &nbsp; Almacén de Productos
      </div>

      {/* ----- BUSCADOR ----- */}
      <div style={{ padding: "15px" }}>
        <input
          type="text"
          placeholder="Buscar por nombre o código de barras..."
          style={{
            width: "100%",
            padding: "10px",
            fontSize: "16px",
            borderRadius: "8px",
            border: "1px solid #ccc"
          }}
        />

        <div style={{ marginTop: "10px" }}>
          <label style={{ fontWeight: "bold" }}>Categoría: </label>
          <select
            style={{
              marginLeft: "10px",
              padding: "8px",
              borderRadius: "8px",
              border: "1px solid #ccc"
            }}
          >
            <option>Todos</option>
            <option>Frutas</option>
            <option>Lácteos</option>
            <option>Panadería</option>
          </select>
        </div>
      </div>

      {/* ----- CARDS DE ESTADÍSTICA ----- */}
      <div style={{
        margin: "0 15px",
        display: "flex",
        gap: "10px",
        justifyContent: "space-between",
      }}>
        {/* Total productos */}
        <div style={cardStyle}>
          📦<br />
          <strong>5</strong><br />
          Total Productos
        </div>

        {/* Stock bajo */}
        <div style={cardStyle}>
          ⚠️<br />
          <strong>0</strong><br />
          Stock Bajo
        </div>

        {/* Valor total */}
        <div style={cardStyle}>
          💲<br />
          <strong>$541.10</strong><br />
          Valor Total
        </div>
      </div>

      {/* ----- LISTA DE PRODUCTOS ----- */}
      <div style={{ marginTop: "20px", padding: "0 15px" }}>
        {productos.map((p, index) => (
          <div key={index} style={productoCard}>
            <div style={{ display: "flex", alignItems: "center" }}>
              <span style={{ fontSize: "32px", marginRight: "10px" }}>{p.icono}</span>
              <div>
                <strong style={{ fontSize: "18px" }}>{p.nombre}</strong><br />
                <span style={{ color: "#555" }}>{p.categoria}</span><br />
                <span style={{ color: "#1a73e8", fontWeight: "bold" }}>
                  Stock: {p.stock} &nbsp; • &nbsp; ${p.precio}
                </span><br />
                <span style={{ fontSize: "12px", color: "#666" }}>
                  Vence en: {p.vencimiento}
                </span>
              </div>
            </div>

            <button style={botonFlotanteDerecha}>⋮</button>
          </div>
        ))}
      </div>

      {/* ----- BOTÓN AZUL FLOTANTE ----- */}
      <button style={botonAgregar}>+</button>

      {/* Botón regresar */}
      <Link to="/">
        <button style={botonVolver}>Volver</button>
      </Link>
    </div>
  );
}

/* === ESTILOS PREDEFINIDOS === */
const cardStyle = {
  background: "white",
  padding: "15px",
  borderRadius: "12px",
  width: "32%",
  textAlign: "center",
  fontSize: "14px",
  boxShadow: "0px 2px 5px rgba(0,0,0,0.1)"
};

const productoCard = {
  background: "#ffffff",
  padding: "15px",
  marginBottom: "10px",
  borderRadius: "12px",
  display: "flex",
  justifyContent: "space-between",
  alignItems: "center",
  boxShadow: "0px 2px 5px rgba(0,0,0,0.1)"
};

const botonFlotanteDerecha = {
  background: "#1a73e8",
  color: "white",
  border: "none",
  padding: "8px",
  borderRadius: "50%",
  cursor: "pointer",
  fontSize: "18px",
};

const botonAgregar = {
  position: "fixed",
  bottom: "20px",
  right: "20px",
  width: "55px",
  height: "55px",
  background: "#1a73e8",
  color: "white",
  borderRadius: "50%",
  fontSize: "30px",
  border: "none",
  cursor: "pointer",
  boxShadow: "0px 2px 8px rgba(0,0,0,0.2)",
};

const botonVolver = {
  position: "fixed",
  bottom: "20px",
  left: "20px",
  width: "100px",
  height: "40px",
  background: "#555",
  color: "white",
  borderRadius: "10px",
  border: "none",
  cursor: "pointer",
};