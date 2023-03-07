const ctx = document.getElementById('myChart');

new Chart(ctx, {
  type: 'line',
  data: {
    labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
    datasets: [{
      label: '# of Votes',
      data: [12, 19, 3, 5, 2, 3],
      borderWidth: 1
    }]
  },
  options: {
    scales: {
      y: {
        beginAtZero: true
      }
    }
  }
});

document.addEventListener('DOMContentLoaded', () => {
  const range = document.getElementById('rollrange');
  const valueSpan = document.getElementById('rollvalue');
  range.addEventListener('input', (event) => {
    const value = event.target.value;
    valueSpan.textContent = `${value}`;
    const offset = ((value - range.min +3) / (range.max - range.min +5)) * range.offsetWidth;
    valueSpan.style.transform = `translateX(${offset}px) translatey(-120%)`;
  });
});