const ctx = document.getElementById('lightchart');

new Chart(ctx, {
  type: 'line',
  data: {
    labels: ['1', '2', '3', '4', '5', '6'],
    datasets: [
      {
        label: 'status',
        data: ['ON', 'ON', 'OFF', 'ON', 'OFF', 'OFF', 'ON'],
        fill: false,
        stepped: true,
      }
    ]
  },
  options: {
    responsive: true,
    plugins: {
      tooltip: {
        mode: 'index',
        intersect: false
      },
    },
    hover: {
      mode: 'index',
      intersec: false
    },
    scales: {
      x: {
        title: {
          display: true,
          text: 'hour'
        }
      },
      y: {
        type: 'category',
        labels: ['ON', 'OFF'],
      }
    }
  },
});
const rtx = document.getElementById('rollchart');

new Chart(rtx, {
  type: 'line',
  data: {
    labels: ['1', '2', '3', '4', '5', '6'],
    datasets: [
      {
        label: '%',
        data: [0, 20, 100, 80, 30, 100],
        fill: false,
      }
    ]
  },
  options: {
    responsive: true,
    plugins: {
      tooltip: {
        mode: 'index',
        intersect: false
      },
    },
    hover: {
      mode: 'index',
      intersec: false
    },
    scales: {
      x: {
        title: {
          display: true,
          text: 'hour'
        }
      },
    }
  },
});
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
    valueSpan.style.transform = `translateX(${offset}px) translatey(-120%)`;
  });
});