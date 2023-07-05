package room.service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServer;
import io.vertx.core.http.ServerWebSocket;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import jssc.SerialPortException;

public class HTTPService extends AbstractVerticle {

	private int port;
	private SerialService serial;
	private ServerWebSocket clientWebSocket;

	public HTTPService(int port, SerialService serial) {
		this.port = port;
		this.serial = serial;
	}

	@Override
	public void start() {
		HttpServer server = vertx.createHttpServer();

		server.webSocketHandler(webSocket -> {
			if (clientWebSocket == null) {
				clientWebSocket = webSocket;

				webSocket.textMessageHandler(this::handleWebSocketMessage);
				webSocket.closeHandler(this::handleWebSocketClose);
			} else {
				webSocket.reject();
			}
		});

		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.post("/api/data_from_client").handler(this::handleReceiveData);

		server.requestHandler(router).listen(port);

		log("Service ready on port: " + port);
	}

	private void handleWebSocketMessage(String message) {
		// Gestisci i messaggi ricevuti dal client
		// Puoi aggiungere la tua logica personalizzata qui
	}

	private void handleWebSocketClose(Void unused) {
		clientWebSocket = null;
	}

	private void handleReceiveData(RoutingContext routingContext) {
		final String origin = routingContext.request().getHeader("Origin");
		try {
			serial.sendMsg(routingContext.body().asString());
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		routingContext.response().setStatusCode(201).putHeader("Access-Control-Allow-Origin", origin)
				.putHeader("content-type", "application/json").end();
	}

	public void addMeasure(String jsonMeasure) {
		if (clientWebSocket != null) {
			clientWebSocket.writeTextMessage(jsonMeasure);
		}
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] " + msg);
	}
}
