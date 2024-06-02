import useTempData from "../hooks/useTempData";

import { Outlet, useNavigate } from "react-router-dom";
import Loading from "./Loading";

function Home() {
  const {
    tempData,
    isLoading,
    threshold,
    toast,
    onChangeThreshold,
    submitForm,
  } = useTempData();

  return (
    <>
      {isLoading ? (
        <Loading />
      ) : (
        <div className="d-flex flex-column justify-content-center align-items-center">
          <div
            className="d-flex gap-3 card p-2"
            style={{ height: "fit-content" }}
          >
            <span className="display-6">
              Temp Data: {""}
              <label htmlFor="" style={{ fontWeight: "bold" }}>
                {tempData} °C
              </label>
            </span>
            <div className="d-flex gap-2 align-items-center justify-content-center">
              <div className="d-flex align-items-center justify-content-center">
                <span className="h5 m-0 ms-1">
                  Temperature Threshold: {`${threshold}`}°C
                </span>
              </div>
            </div>
          </div>
          <Outlet
            context={{ threshold, toast, onChangeThreshold, submitForm }}
          />
        </div>
      )}
    </>
  );
}

export default Home;
