import { BrowserRouter, Routes, Route } from "react-router-dom";

import InterfazProductos from "./pages/InterfazProductos";
import BusquedaProductos from "./pages/BusquedaProductos";
import CajaRegistradora from "./pages/CajaRegistradora";
import ResumenCompra from "./pages/ResumenCompra";
import ConfirmarVenta from "./pages/ConfirmarVenta";
import AlmacenProductos from "./pages/AlmacenProductos";
import PantallaFinal from "./pages/pantallaFinal";
import InterfazProductosCaja from "./pages/InterfazProductosCaja";

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<InterfazProductos />} />
        <Route path="/buscar" element={<BusquedaProductos />} />
        <Route path="/caja" element={<CajaRegistradora />} />
        <Route path="/resumen" element={<ResumenCompra />} />
        <Route path="/confirmar" element={<ConfirmarVenta />} />
        <Route path="/almacen" element={<AlmacenProductos />} />
        <Route path="/final" element={<PantallaFinal />} />
        <Route path="/productos-caja" element={<InterfazProductosCaja />} />
      </Routes>
    </BrowserRouter>
  );
}