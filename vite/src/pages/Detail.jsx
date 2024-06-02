import React, { useEffect, useState } from "react";
import { Toast } from "primereact/toast";

import { InputSwitch } from "primereact/inputswitch";

function Detail({
  toast,
  onPlusThreshold,
  disableThreshold,
  onMinsThreshold,
  setThreshold,
  threshold,
  submitForm,
  tempData,
}) {
  const [checked, setChecked] = useState(false);

  useEffect(() => {
    if (threshold === 0) {
      setChecked(true);
    } else {
      setChecked(false);
    }
    setThreshold(tempData.threshold);
  }, []);

  return (
    <>
      <Toast ref={toast} />

      <div className="d-flex flex-column p-3 h-100">
        <div className="d-flex ms-3 mt-3">
          <span className="m-0 h3" style={{ fontWeight: "bold" }}>
            Threshold Settings
          </span>
        </div>
        <div
          style={{
            justifyContent: "space-evenly",
            opacity: checked ? "0.5" : "1",
          }}
          className="d-flex mt-4 p-3 gap-5 align-items-center"
        >
          <div className="d-flex w-50 justify-content-center">
            <i className="pi pi-minus" onClick={() => onMinsThreshold()}></i>
          </div>
          <div
            className="w-100 card justify-content-center align-items-center "
            style={{
              height: "90px",
              display: "flex!important",
              borderRadius: "100rem",
            }}
          >
            <span className="m-0 h1">{threshold}°c</span>
          </div>
          <div className="d-flex w-50 justify-content-center">
            <i
              className="pi pi-plus"
              onClick={() => {
                onPlusThreshold();
              }}
            ></i>
          </div>
        </div>

        <div
          className="d-flex h-100 gap-2 mx-4 mt-5"
          style={{ justifyContent: "space-between" }}
        >
          <div className="d-flex">
            <span style={{ fontWeight: "bold" }}>Disable Threshold</span>
          </div>
          <div className="">
            <InputSwitch
              checked={threshold === 0 ? checked : null}
              onChange={(e) => {
                setChecked(e.value);
                if (e.value === true) {
                  setThreshold(0);
                } else {
                  setThreshold(50);
                }
              }}
            />
          </div>
        </div>
        <div className="d-flex justify-content-center align-items-center  mt-3 w-100">
          <button
            className="btn btn-primary"
            onClick={() => {
              submitForm(threshold);
            }}
          >
            Save Changes
          </button>
        </div>
      </div>
    </>
  );
}

export default Detail;
