function DateDisplay() {
  const date = new Date();
  const day = date.getDate();
  const monthIndex = date.getMonth();
  const year = date.getFullYear();

  // Array of month names
  const monthNames = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December",
  ];

  const monthName = monthNames[monthIndex];

  return { day, month: monthName, year };
}

export default DateDisplay;
