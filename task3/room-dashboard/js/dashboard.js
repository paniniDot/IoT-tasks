function createJson(obj, value) {
  const json = {
    name: obj,
    measure: value,
  }
  return JSON.stringify(json);
}

document.addEventListener('DOMContentLoaded', () => {

  const rollButton = document.getElementById("rollcheck");
  const lightswitch = document.getElementById("lightswitch");
  const lightButton = document.getElementById("lightcheck");
  const lightbulbIcon = document.querySelector(".bi-lightbulb-off");

  lightButton.addEventListener("click", () => {
    lightswitch.addEventListener("click", () => {
      if (lightButton.checked) {
        webSocket.sendMessage(createJson("light", lightswitch.checked ? 1 : 0));
        lightbulbIcon.classList.replace(
          lightswitch.checked ? "bi-lightbulb-off" : "bi-lightbulb",
          lightswitch.checked ? "bi-lightbulb" : "bi-lightbulb-off"
        );
      }
    });
    webSocket.sendMessage(createJson("manual_light", lightButton.checked ? 1 : 0));
  });

  rollButton.addEventListener("click", () => {
    const range = document.getElementById('rollrange');
    const valueSpan = document.getElementById('rollvalue');
    range.addEventListener('input', (event) => {
      if(rollButton.checked) {
        const value = event.target.value;
        webSocket.sendMessage(createJson("roll", value));
        valueSpan.textContent = `${value}`;
        const offset = ((value - range.min + 2) / (range.max - range.min + 4)) * range.offsetWidth;
        valueSpan.style.transform = `translateX(${offset}px) translateY(-120%)`;
      }
    });
    webSocket.sendMessage(createJson("manual_roll", rollButton.checked ? 1 : 0));
  });
});