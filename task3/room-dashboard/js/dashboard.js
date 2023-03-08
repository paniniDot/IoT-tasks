const ctx = document.getElementById('myChart');

new Chart(ctx, {
  type: 'line',
  data: {
    labels: ['1', '2', '3', '4', '5', '6'],
    datasets: [
      {
        label: 'status',
        data: [0, 1, 0, 1],
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
      title: {
        display: true,
        text: 'light'
      }
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
        title: {
          display: true,
          text: 'light'
        },
        min: 0,
        max: 1,
        ticks: {
          stepSize: 1
        }
      }
    }
  },
});

document.addEventListener('DOMContentLoaded', () => {
  const range = document.getElementById('rollrange');
  const valueSpan = document.getElementById('rollvalue');
  range.addEventListener('input', (event) => {
    const value = event.target.value;
    valueSpan.textContent = `${value}`;
    const offset = ((value - range.min + 2.5) / (range.max - range.min + 4.5)) * range.offsetWidth;
    valueSpan.style.transform = `translateX(${offset}px) translatey(-120%)`;
  });
});