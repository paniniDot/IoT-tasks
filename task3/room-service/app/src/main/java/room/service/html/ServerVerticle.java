package room.service.html;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.BodyHandler;

public class ServerVerticle extends AbstractVerticle {

    @Override
    public void start() {
        Router router = Router.router(vertx);

        // Enable body handling to automatically parse JSON payloads
        router.route().handler(BodyHandler.create());

        // Handle the POST request
        router.post("/api/user").handler(ctx -> {
            // Get the JSON payload from the request body
            User user = ctx.getBodyAsJson().mapTo(User.class);

            // Process the user data
            // ...

            // Send the response
            HttpServerResponse response = ctx.response();
            response.setStatusCode(200).end();
        });

        // Start the server
        vertx.createHttpServer().requestHandler(router).listen(8080, ar -> {
            if (ar.succeeded()) {
                System.out.println("Server started on port 8080");
            } else {
                System.err.println("Failed to start server: " + ar.cause().getMessage());
            }
        });
    }
}
