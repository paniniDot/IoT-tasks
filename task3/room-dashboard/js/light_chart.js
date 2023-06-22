const data_light = [
    {
      x: [],
      y: [],
      mode: 'lines+markers',
      line: {
        color: 'red',
        shape: 'linear'
      }
    }
  ];
  
  const layout_light = {
    title: 'Storico luce',
    xaxis: {
      type: 'category',
      tickformat: '%Y-%m-%d %H:%M:%S'
    },
    yaxis: {
        title: 'Valore',
        type: 'category'
      }
  };
  
  let counter_light = 0;
  
  function updateLightChart(time, value) {
    data_light[0].x.push(time);
    data_light[0].y.push(value);
  
    // Ridimensiona il grafico se supera 10 valori
    if (data_light[0].x.length > 15) {
        data_light[0].x.shift();
        data_light[0].y.shift();
    }
  
    Plotly.update('lightchart', data_light, layout_light);
    console.log(data_light);
  }
  
  Plotly.newPlot('lightchart', data_light, layout_light);
  
  setInterval(function () {
    axios.get('http://localhost:8080/api/data')
    .then(response => {
      // Dati ricevuti dal server
      const data = response.data;
      console.log(data);
      const time = convertTimestampToFormattedDate(data.timestamp);
      const measure = data.measure;
      const name = data.name;
      if(name == "light") {
        updateLightChart(time, measure);
      }
    })
    .catch(error => {
      // Gestire eventuali errori
      console.error(error);
    });
  }, 1000);
  
  function convertTimestampToFormattedDate(timestamp) {
    const date = new Date(timestamp); // Moltiplica per 1000 per convertire da millisecondi a secondi
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0'); // Aggiunge uno zero iniziale se necessario
    const day = String(date.getDate()).padStart(2, '0');
    const hours = String(date.getHours()).padStart(2, '0');
    const minutes = String(date.getMinutes()).padStart(2, '0');
    const seconds = String(date.getSeconds()).padStart(2, '0');
    
    const formattedDate = `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    return formattedDate;
  }