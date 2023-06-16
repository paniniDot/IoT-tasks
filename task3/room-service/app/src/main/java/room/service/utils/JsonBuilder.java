package room.service.utils;

import com.google.gson.JsonParser;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class JsonBuilder {

	public static String getJsonWithTimestamp(String json) {
	    JsonElement jsonEl = JsonParser.parseString(json);
	    if (jsonEl.isJsonObject()) {
	        JsonObject jsonObj = jsonEl.getAsJsonObject();
	        jsonObj.addProperty("timestamp", System.currentTimeMillis());
	        return jsonObj.toString();
	    }
	    return null;
	}

}
