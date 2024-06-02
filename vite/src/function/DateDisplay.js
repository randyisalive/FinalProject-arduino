function DateDisplay() {
  const date = new Date();
  const day = date.getDate();
  const month = date.getMonth() + 1; // Remember to add 1 since months are 0-indexed
  const year = date.getFullYear();
}
