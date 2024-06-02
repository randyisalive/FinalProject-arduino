import { Link } from "react-router-dom";

function Footer() {
  return (
    <>
      <div
        className="d-flex border-top p-3 card m-3 flex-row rounded-8"
        style={{ justifyContent: "space-evenly" }}
      >
        <div className="d-flex">
          <Link className="text-dark" to={`/`}>
            <i className="pi pi-home" style={{ fontSize: "2rem" }}></i>
          </Link>
        </div>
        <div className="d-flex">
          <Link className="text-dark" to={`settings`}>
            <i className="pi pi-cog" style={{ fontSize: "2rem" }}></i>
          </Link>
        </div>
        <div className="d-flex">
          <i className="pi pi-car" style={{ fontSize: "2rem" }}></i>
        </div>
        <div className="d-flex">
          <Link className="text-dark" to={`/user/rei`}>
            <i className="pi pi-user" style={{ fontSize: "2rem" }}></i>
          </Link>
        </div>
      </div>
    </>
  );
}

export default Footer;
