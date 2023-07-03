package room.service.html;

import io.vertx.core.AbstractVerticle;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

import java.util.LinkedList;
/*
 * Data Service as a vertx event-loop 
 */
public class DataService extends AbstractVerticle {

	private int port;
	private LinkedList<String> values_to_send;
	private LinkedList<String> received_values;
	
	public DataService(int port) {
		this.values_to_send = new LinkedList<>();	
		this.received_values = new LinkedList<>();
		this.port = port;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.get("/api/data").handler(this::handleSendData);
		router.post("/api/data").handler(this::handleReceiveData);
		vertx.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}
	
	public void addMeasure(String jsonMeasure) {
		this.values_to_send.addFirst(jsonMeasure);
	}
	
	private void handleSendData(RoutingContext routingContext) {
		final String origin = routingContext.request().getHeader("Origin");
		routingContext.response()
			.putHeader("Access-Control-Allow-Origin", origin)
			.putHeader("content-type", "application/json")
			.end(this.values_to_send.getFirst());
	}
	
	public String getMeasure() {
		return this.received_values.getFirst();
	}
	
	public boolean isMeasureAvailable() {
		return !this.received_values.isEmpty();
	}
	
	private void handleReceiveData(RoutingContext routingContext) {
		this.received_values.addFirst(routingContext.body().asString());
		routingContext.response().setStatusCode(201).end();
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}

}