import { BrowserRouter, Routes, Route } from "react-router-dom";

import InterfazProductos from "./pages/InterfazProductos";
import BusquedaProductos from "./pages/BusquedaProductos";
import CajaRegistradora from "./pages/CajaRegistradora";
import ResumenCompra from "./pages/ResumenCompra";
import ConfirmarVenta from "./pages/ConfirmarVenta";
import AlmacenProductos from "./pages/AlmacenProductos";

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
      </Routes>
    </BrowserRouter>
  );
}