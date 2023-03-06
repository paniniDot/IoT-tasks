package room.service.json;

import java.util.Date;

public interface JsonHandler<T> {
	
	public String getSource(String json);
	
	public T getMeasure(String json);
	
	public Date getDate(String json);
	
}
