
document.addEventListener('DOMContentLoaded', () => {

  const rollButton = document.getElementById("rollcheck");
  const lightswitch = document.getElementById("lightswitch");
  const lightButton = document.getElementById("lightcheck");
  const lightbulbIcon = document.querySelector(".bi-lightbulb-off");


  lightButton.addEventListener("click", () => {
    let manual_light = false;
    if (lightButton.checked) {
      manual_light = true;
      lightswitch.addEventListener("click", () => {
        if (manual_light == true) {
          const value = lightswitch.checked ? 1 : 0;
          const jsonData = createJson("light", value);
          axios.post('http://localhost:8080/api/data', jsonData)
            .then(response => {
              console.log("messaggio inviato");
            })
            .catch(error => {
              console.error(error);
            });
          lightbulbIcon.classList.replace(
            lightswitch.checked ? "bi-lightbulb-off" : "bi-lightbulb",
            lightswitch.checked ? "bi-lightbulb" : "bi-lightbulb-off"
          );
        }
      });
    }
    const value = manual_light ? 1 : 0;
    const jsonData = createJson("manual_light", value);
    axios.post('http://localhost:8080/api/data', jsonData)
      .then(response => {
        console.log("messaggio inviato");
      })
      .catch(error => {
        console.error(error);
      });
  });

  function createJson(obj, value) {
    const json = {
      name: obj,
      measure: value,
    }
    return JSON.stringify(json);
  }

  rollButton.addEventListener("click", () => {
    if (rollButton.checked) {
      const range = document.getElementById('rollrange');
      const valueSpan = document.getElementById('rollvalue');
      range.addEventListener('input', (event) => {
        const value = event.target.value;

        axios.post('http://localhost:8080/api/data', createJson("roll", value))
          .then(response => {
            log("messaggio inviato");
          })
          .catch(error => {
            console.error(error);
          });

        valueSpan.textContent = `${value}`;
        const offset = ((value - range.min + 2) / (range.max - range.min + 4)) * range.offsetWidth;
        valueSpan.style.transform = `translateX(${offset}px) translateY(-120%)`;
      });
    }
  });
});