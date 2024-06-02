import React, { useEffect, useRef, useState } from "react";
import global_const from "../global_const";
const { base_url } = global_const();

function useTempData() {
  const [tempData, setTempData] = useState([]);
  const [isLoading, setIsLoading] = useState(true);
  const [threshold, setThreshold] = useState(50);

  // toast
  const toast = useRef(null);
  const show = () => {
    toast.current.show({
      severity: "success",
      summary: "Info",
      detail: `Threshold change!! ${threshold} °C`,
    });
  };

  function onChangeThreshold(e) {
    setThreshold(e.value);
    console.log(threshold);
  }
  function onPlusThreshold() {
    setThreshold((prev) => prev + 1);
    console.log(threshold);
  }
  function onMinsThreshold() {
    setThreshold((prev) => prev - 1);
    console.log(threshold);
  }

  function disableThreshold() {
    setThreshold(0);
    console.log(threshold);
  }

  // send to server POST
  function submitForm() {
    change_threshold(threshold).then((data) => {
      console.log(data);
      show();
    });
  }

  useEffect(() => {
    // Correctly set the interval to run every 5 seconds
    const intervalId = setInterval(() => {
      get_data().then((data) => {
        setTempData(data);
        setIsLoading(false);
        console.log(data);
      });
    }, 2000); // 2000 milliseconds delay / 2 seconds delay

    // Clear the interval on component unmount
    return () => clearInterval(intervalId);
  }, []); // Empty dependency array to run only once on mount

  return {
    tempData,
    isLoading,
    onChangeThreshold,
    submitForm,
    threshold,
    toast,
    onMinsThreshold,
    onPlusThreshold,
    disableThreshold,
    setThreshold,
  };
}

async function get_data() {
  try {
    const response = await fetch(`${base_url}/get`);
    const data = await response.json();
    return data;
  } catch (e) {
    console.error(e);
  }
}

async function change_threshold(threshold) {
  try {
    const response = await fetch(`${base_url}/send_threshold`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ threshold }),
    });
    const data = await response.json();
    return data;
  } catch (e) {
    console.error(e);
  }
}

export default useTempData;
