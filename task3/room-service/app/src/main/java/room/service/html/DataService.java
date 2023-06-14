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
	private LinkedList<String> values;
	
	public DataService(int port) {
		values = new LinkedList<>();		
		this.port = port;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.get("/api/data").handler(this::handleGetData);		
		vertx.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}
	
	public void addMeasure(String jsonMeasure) {
		this.values.addFirst(jsonMeasure);
	}
	
	private void handleGetData(RoutingContext routingContext) {
		final String origin = routingContext.request().getHeader("Origin");
		routingContext.response()
			.putHeader("Access-Control-Allow-Origin", origin)
			.putHeader("content-type", "application/json")
			.end(this.values.getFirst());
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] "+msg);
	}

}