import useTempData from "../hooks/useTempData";

import { Outlet } from "react-router-dom";
import Loading from "./Loading";
import DeviceCard from "../components/DeviceCard";
import DateDisplay from "../function/DateDisplay";

function Home({ isLoading, tempData }) {
  const { day, month, year } = DateDisplay();
  return (
    <>
      {isLoading ? (
        <Loading />
      ) : (
        <div className="d-flex flex-column h-100 p-4">
          <div
            className="d-flex w-100"
            style={{ justifyContent: "space-between" }}
          >
            <div className="d-flex w-100">
              <div className="d-flex w-100">
                <span
                  className="m-0 display-5"
                  style={{ height: "fit-content" }}
                >
                  Good morning,
                </span>
              </div>
            </div>
            <div
              className="d-flex w-50 justify-content-end"
              style={{ height: "fit-content" }}
            >
              <span
                className="m-0  text-end"
                style={{
                  fontSize: "12px",
                  width: "50px",
                  justifyContent: "end",
                  height: "fit-content",
                }}
              >
                {day} {month} {year}
              </span>
            </div>
          </div>
          <div className="d-flex">
            <div
              className="d-flex w-100"
              style={{ justifyContent: "space-between" }}
            >
              <span className="m-0 display-5" style={{ fontWeight: "bold" }}>
                Rei!
              </span>
              {/* <span
                className="m-0"
                style={{ fontSize: "18px", fontWeight: "bold" }}
              >
                {"22"}° C
              </span> */}
            </div>
          </div>
          {/* this is for the device card */}
          <DeviceCard href={`/device/1`} tempData={tempData} />
        </div>
      )}

      {/*   {isLoading ? (
        <Loading />
      ) : (
        <div className="d-flex flex-column justify-content-center align-items-center">
          <div
            className="d-flex gap-3 flex-column p-2"
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
                <span className="h5 m-0">
                  Temperature Threshold: {`${threshold}`}°C
                </span>
              </div>
            </div>
          </div>
          <Outlet
            context={{ threshold, toast, onChangeThreshold, submitForm }}
          />
        </div>
      )} */}
    </>
  );
}

export default Home;
