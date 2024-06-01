import React, { useEffect, useState } from "react";
import global_const from "../global_const";

function useTempData() {
  const { base_url } = global_const();
  const [tempData, setTempData] = useState([]);

  async function get_data() {
    try {
      const response = await fetch(`${base_url}/get`);
      const data = await response.json();
      return data;
    } catch (e) {
      console.error(e);
    }
  }

  useEffect(() => {
    // Correctly set the interval to run every 5 seconds
    const intervalId = setInterval(() => {
      get_data().then((data) => {
        setTempData(data.value);
        console.log(data);
      });
    }, 2000); // 5000 milliseconds delay

    // Clear the interval on component unmount
    return () => clearInterval(intervalId);
  }, []); // Empty dependency array to run only once on mount

  return { tempData };
}

export default useTempData;
