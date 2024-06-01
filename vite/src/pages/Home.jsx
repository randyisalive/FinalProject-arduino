import React from "react";
import useTempData from "../hooks/useTempData";

function Home() {
  const { tempData } = useTempData();
  return (
    <>
      <div>Temp Data: {tempData} C</div>
    </>
  );
}

export default Home;
