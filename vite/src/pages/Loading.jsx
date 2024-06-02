import { ProgressSpinner } from "primereact/progressspinner";

function Loading() {
  return (
    <div
      className="vw-100 vh-100 justify-content-center align-items-center"
      style={{
        backgroundColor: "rgba(0,0,0,0.01)",
        zIndex: "9999",
        display: "flex",
        position: "absolute",
      }}
    >
      <ProgressSpinner />
    </div>
  );
}

export default Loading;
