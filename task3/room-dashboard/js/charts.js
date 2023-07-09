const chartData = {
  roll: {
    data: [
      {
        x: [],
        y: [],
        type: 'bar',
      }
    ],
    layout: {
      title: 'Storico tenda',
      xaxis: {
        title: 'giorno-ora',
        type: 'category',
        tickformat: '%D-%H'
      },
      yaxis: {
        title: 'aperto in %',
        range: [0, 100]
      }
    },
  },
  light: {
    data: [
      {
        x: [],
        y: [],
        type: 'bar',
      }
    ],
    layout: {
      title: 'Storico luce',
      xaxis: {
        title: 'giorno-ora',
        type: 'category',
        tickformat: '%D-%H'
      },
      yaxis: {
        title: 'acceso in %',
        range: [0, 100]
      }
    },
  }
};

function initializeChart(chartId, data, layout) {
  Plotly.newPlot(chartId, data, layout, { displayModeBar: true,
    responsive: true });
}

function updateChart(chartId, data, layout, time, value) {
  const date = new Date(time);
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0');
  const day = String(date.getDate()).padStart(2, '0');
  const hours = String(date.getHours()).padStart(2, '0');
  const minutes = String(date.getMinutes()).padStart(2, '0');
  const seconds = String(date.getSeconds()).padStart(2, '0');
  if(value>0){
    data[0].x.push(`${day}-${hours}`);
    data[0].y.push((1 / 3600) * 100);
  }
  if (data[0].x.length > 24) {
    data[0].x.shift();
    data[0].y.shift();
  }
  Plotly.update(chartId, data, layout);
}

// Inizializza i grafici
initializeChart('lightchart', chartData.light.data, chartData.light.layout);
initializeChart('rollchart', chartData.roll.data, chartData.roll.layout);