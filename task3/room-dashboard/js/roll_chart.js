const data = [
  {
    x: [],
    y: [],
    mode: 'lines',
    line: {
      color: 'blue'
    }
  }
];

const layout = {
  xaxis: {
    type: 'category',
    title: 'Storico tenda',
    tickformat: '%Y-%m-%d %H:%M'
  },
  yaxis: {
    title: '%'
  }
};

function updateRollChart(time, value) {
  data[0].x.push(time);
  data[0].y.push(value);
  Plotly.update('rollchart', data, layout);
}

Plotly.newPlot('rollchart', data, layout);

setInterval(function () {
  axios.get('http://localhost:8080/api/data')
  .then(response => {
    // Dati ricevuti dal server
    const data = response.data;
    console.log(data);
  })
  .catch(error => {
    // Gestire eventuali errori
    console.error(error);
  });
}, 1000);

function convertTimestampToFormattedDate(timestamp) {
  const date = new Date(timestamp * 1000); // Moltiplica per 1000 per convertire da millisecondi a secondi
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0'); // Aggiunge uno zero iniziale se necessario
  const day = String(date.getDate()).padStart(2, '0');
  const hours = String(date.getHours()).padStart(2, '0');
  const minutes = String(date.getMinutes()).padStart(2, '0');
  
  const formattedDate = `${year}-${month}-${day} ${hours}:${minutes}`;
  return formattedDate;
}