import "./App.css";
import "mdb-react-ui-kit/dist/css/mdb.min.css";
import "primeicons/primeicons.css";
import "primereact/resources/themes/lara-light-cyan/theme.css";

import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Home from "./pages/Home";
import Setting from "./pages/Setting";
import Footer from "./components/Footer";
import Header from "./components/Header";
import Loading from "./pages/Loading";
import User from "./pages/User";

function App() {
  return (
    <>
      <Router>
        <div
          className="d-flex flex-column vh-100"
          style={{ justifyContent: "space-between" }}
        >
          <Header />
          <Routes>
            <Route path="/" element={<Home />}>
              <Route path="settings" element={<Setting />} />
            </Route>
            <Route path="/user/:user_name" element={<User />} />
          </Routes>
          <Footer />
        </div>
      </Router>
    </>
  );
}

export default App;
