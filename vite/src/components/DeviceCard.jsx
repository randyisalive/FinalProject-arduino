import React from "react";
import { Link } from "react-router-dom";

function DeviceCard({ tempData, href }) {
  return (
    <Link to={`${href}`} className="text-black">
      <div
        className="d-flex w-100 gap-3 h-100 flex-column mt-5"
        style={{ overflowY: "scroll", maxHeight: "350px", minHeight: "50%" }}
      >
        <div
          className="card p-3 d-flex flex-column"
          style={{ justifyContent: "space-between" }}
        >
          <div className="d-flex w-100">
            <div className="d-flex flex-column gap-2 w-100">
              <img
                src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTcYJalLS9g1MD9U_Y0CWmXggihJNbLhXUy6w&s"
                alt=""
                width={50}
              />
              <span
                className="m-0 text-danger"
                style={{ fontSize: "15px", fontWeight: "bold" }}
              >
                TIRE TEMPERATURE
              </span>
            </div>
            <div className="d-flex h-100">
              <i
                className="pi pi-ellipsis-v"
                style={{ color: "#e3e3e3" }}
                onClick={(e) => {
                  e.preventDefault();
                }}
              ></i>
            </div>
          </div>
          <div className="d-flex w-100 gap-2 " style={{ height: "2rem" }}>
            <div className="d-flex align-items-end justify-content-end">
              <p className="m-0" style={{ fontWeight: "bold" }}>
                {tempData.value}
              </p>
            </div>

            <div className="d-flex align-items-end">
              <span
                className="m-0"
                style={{
                  fontSize: "8px",
                  fontWeight: "bold",
                  paddingBottom: "0.2rem",
                }}
              >
                CELCIUS
              </span>
            </div>
          </div>
          <div className="d-flex w-100 gap-2 " style={{ height: "2rem" }}>
            <div className="d-flex align-items-end justify-content-end">
              <p className="m-0" style={{ fontWeight: "bold" }}>
                {tempData.threshold}°C
              </p>
            </div>

            <div className="d-flex align-items-end">
              <span
                className="m-0"
                style={{
                  fontSize: "8px",
                  fontWeight: "bold",
                  paddingBottom: "0.2rem",
                }}
              >
                THRESHOLD
              </span>
            </div>
          </div>
        </div>
      </div>
    </Link>
  );
}

export default DeviceCard;
