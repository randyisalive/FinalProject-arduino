import { Slider } from "primereact/slider";
import { useOutletContext } from "react-router-dom";

import { Toast } from "primereact/toast";

function Setting() {
  const { threshold, onChangeThreshold, submitForm, toast } =
    useOutletContext();
  return (
    <>
      <Toast ref={toast} />
      <div className="d-flex mt-3 flex-column mt-5 p-2 gap-3">
        <div className=" card flex justify-content-center">
          <Slider
            value={threshold}
            step={10}
            onChange={(e) => onChangeThreshold(e)}
            className="w-14rem"
          />
        </div>
        <div className="d-block ">
          <button className="btn btn-primary" onClick={() => submitForm()}>
            Change Threshold
          </button>
        </div>
      </div>
    </>
  );
}

export default Setting;
