import "./App.css";
import "mdb-react-ui-kit/dist/css/mdb.min.css";
import "primeicons/primeicons.css";
import "@fortawesome/fontawesome-free/css/all.min.css";
import "primereact/resources/themes/lara-light-cyan/theme.css";

import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import Footer from "./components/Footer";
import Header from "./components/Header";
import User from "./pages/User";
import Detail from "./pages/Detail";
import useTempData from "./hooks/useTempData";

function App() {
  const {
    tempData,
    isLoading,
    threshold,
    onMinsThreshold,
    onPlusThreshold,
    setThreshold,
    submitForm,
    toast,
  } = useTempData();
  return (
    <>
      <Router>
        <div
          className="d-flex flex-column vh-100"
          style={{ justifyContent: "space-between" }}
        >
          <Header />
          <Routes>
            <Route
              path="/"
              element={<Home isLoading={isLoading} tempData={tempData} />}
            />
            <Route
              path="/device/:device"
              element={
                <Detail
                  threshold={threshold}
                  onMinsThreshold={onMinsThreshold}
                  onPlusThreshold={onPlusThreshold}
                  setThreshold={setThreshold}
                  submitForm={submitForm}
                  toast={toast}
                  tempData={tempData}
                />
              }
            />
            <Route path="/user/:user_name" element={<User />} />
          </Routes>
          <Footer />
        </div>
      </Router>
    </>
  );
}

export default App;
