const webSocket = new WebSocket('ws://localhost:8080');

webSocket.onopen = function() {
    console.log('Socket attivo.');
};

webSocket.onerror = function(error) {
    console.error('Errore nella connessione WebSocket:', error);
};

function sendMessage(message) {
  webSocket.send(message);
  console.log('Messaggio inviato:', message);
}
