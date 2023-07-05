const chartData = {
  roll: {
    data: [
      {
        x: [],
        y: [],
        mode: 'lines+markers',
        line: {
          color: 'red',
          shape: 'linear'
        }
      }
    ],
    layout: {
      title: 'Storico tenda',
      xaxis: {
        type: 'category',
        tickformat: '%Y-%m-%d %H:%M:%S'
      },
      yaxis: {
        title: '%'
      }
    },
    counter: 0
  },
  light: {
    data: [
      {
        x: [],
        y: [],
        mode: 'lines+markers',
        line: {
          color: 'red',
          shape: 'linear'
        }
      }
    ],
    layout: {
      title: 'Storico luce',
      xaxis: {
        type: 'category',
        tickformat: '%Y-%m-%d %H:%M:%S'
      },
      yaxis: {
        title: 'Valore',
        type: 'category'
      }
    },
    counter: 0
  }
};

function initializeChart(chartId, data, layout) {
  Plotly.newPlot(chartId, data, layout);
}

function updateChart(chartId, data, layout, time, value) {
  data[0].x.push(time);
  data[0].y.push(value);

  // Ridimensiona il grafico se supera 10 valori
  if (data[0].x.length > 15) {
    data[0].x.shift();
    data[0].y.shift();
  }

  Plotly.update(chartId, data, layout);
}

function handleWebSocketMessage(event) {
  const data = JSON.parse(event.data);
  console.log(data);
  const time = convertTimestampToFormattedDate(data.timestamp);
  const measure = data.measure;
  const name = data.name;
  if (name === "light") {
    const chart = chartData[name];
    updateChart('lightchart', chart.data, chart.layout, time, measure);
  } else if (name === "roll") {
    const chart = chartData[name];
    updateChart('rollchart', chart.data, chart.layout, time, measure);
  }
}

function convertTimestampToFormattedDate(timestamp) {
  const date = new Date(timestamp);
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0');
  const day = String(date.getDate()).padStart(2, '0');
  const hours = String(date.getHours()).padStart(2, '0');
  const minutes = String(date.getMinutes()).padStart(2, '0');
  const seconds = String(date.getSeconds()).padStart(2, '0');

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
}

// Inizializza i grafici
initializeChart('lightchart', chartData.light.data, chartData.light.layout);
initializeChart('rollchart', chartData.roll.data, chartData.roll.layout);

const webSocket = new WebSocket('ws://localhost:8080/api/data_from_server');

webSocket.onmessage = handleWebSocketMessage;
