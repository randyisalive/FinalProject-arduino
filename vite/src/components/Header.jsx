import React from "react";
import { Link } from "react-router-dom";

function Header() {
  return (
    <div
      className="mt-3 d-flex gap-3 pb-2"
      style={{ justifyContent: "space-evenly" }}
    >
      <div className="d-flex align-items-center">
        <i className="pi pi-bars" style={{ fontSize: "18px" }}></i>
      </div>
      <Link to={`/`}>
        <span className="h5 m-0">
          <label htmlFor="" style={{ fontWeight: "bold" }}>
            VEHI
          </label>
          <label htmlFor="">CHECK</label>
        </span>
      </Link>

      <div className="d-flex align-items-center">
        <i className="pi pi-sliders-h" style={{ fontSize: "18px" }}></i>
      </div>
    </div>
  );
}

export default Header;
