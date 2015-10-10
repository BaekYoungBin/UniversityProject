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
	String ID = request.getParameter("ID");
	String select = request.getParameter("select");
	int sel = Integer.valueOf(select);
	String Plane_Type[] = new String[10];
	String leftseat ="null";
	%>
	<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%	
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select Plane_Type from customer_Reservation where c_id ='" + ID +"'");
		int i = 0;
		while (rs.next()){
			Plane_Type[i] = rs.getString("Plane_Type");			
			i++;
		}	
		rs = stmt.executeQuery("select leftseat from flight where Plane_Type ='"+Plane_Type[sel]+"'");
		while (rs.next()){
			leftseat = rs.getString("leftseat");		
		}
		int leftseatint = Integer.valueOf(leftseat);
		leftseatint = leftseatint +1;
		String leftseatstring = String.valueOf(leftseatint);
	
			rs = stmt.executeQuery("UPDATE FLIGHT SET leftseat = '"+leftseatstring+"' where Plane_Type ='"+Plane_Type[sel]+"'");
		rs = stmt.executeQuery("delete from customer_Reservation where PLANE_TYPE = '"+Plane_Type[sel]+"'");
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
	<br> <br> 
	<form action="CustomerMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
	                        
</body>
</html>