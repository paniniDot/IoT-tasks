
document.addEventListener('DOMContentLoaded', () => {
  const lightswitch = document.getElementById("lightswitch");
  const lightbulbIcon = document.querySelector(".bi-lightbulb-off");

  lightswitch.addEventListener("click", () => {
    if (lightswitch.checked) {
      lightbulbIcon.classList.replace("bi-lightbulb-off", "bi-lightbulb");
    } else {
      lightbulbIcon.classList.replace("bi-lightbulb", "bi-lightbulb-off");
    }
  });

  const range = document.getElementById('rollrange');
  const valueSpan = document.getElementById('rollvalue');
  range.addEventListener('input', (event) => {
    const value = event.target.value;
    valueSpan.textContent = `${value}`;
    const offset = ((value - range.min + 2) / (range.max - range.min + 4)) * range.offsetWidth;
    valueSpan.style.transform = `translateX(${offset}px) translateY(-120%)`;
  });
});
