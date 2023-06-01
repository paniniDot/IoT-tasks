package room.service.http;

public interface HttpConnection {

	/**
	 * Send a POST http request to the dashboard with json formatted data
	 * @param uri 
	 * 		the resource identifier of the dashboard
	 * @param json
	 * 		the data to be sent
	 */
	void sendJson(final String uri, final String json);
	
	/**
	 * 
	 * @return a json string containing data sent from the dashboard
	 */
	String getJson();
	
	/**
	 * 
	 * @return true if there's a dashboard json object available to be read.
	 */
	boolean isJsonAvailable();
	
}
