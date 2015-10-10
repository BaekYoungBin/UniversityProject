<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<% 
String tmpID = request.getParameter("ID");
	String select = request.getParameter("select");
	int sel = Integer.valueOf(select);
	String ID[] = new String[10];
	String Plane_Type[] = new String[10];
	%>
	<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%	
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select A_ID, Plane_type, Origin, Destination, F_time, Lead_time from Agency_Reservation");
		int i = 0;
		while (rs.next()){
			ID[i] = rs.getString("A_ID");	
			Plane_Type[i] = rs.getString("Plane_Type");			
			i++;
		}	
		rs = stmt.executeQuery("delete from Agency_Reservation where PLANE_TYPE = '"+Plane_Type[sel]+"' and A_ID = '" + ID[sel] +"'");
		out.println("예약 삭제 완료");
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}		
	%>
	<br> <br> <form action="AgencyMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
</body>
</html>