<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
<%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
	<%
	String ID = request.getParameter("ID");
	String Select = request.getParameter("select");	
	int sel = Integer.valueOf(Select);
	%>
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>비행기 명</th><th>출발지</th><th>목적지</th><th>가격</th><th>남은좌석</th>
	<%

	
	String Plane_Type[] = new String[10];
	String Origin[] = new String[10];
	String Destination[] = new String[10];
	String Cost[] = new String[10];
	String leftseat = "null";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select Plane_Type, Origin, Destination, Cost from customer_cart");
		int i = 0;
		while (rs.next()){
			Plane_Type[i] = rs.getString("Plane_Type");
			Origin[i] = rs.getString("Origin");
			Destination[i] = rs.getString("Destination");
			Cost[i] = rs.getString("Cost");
			i++;
		}
		rs.close();
		rs = stmt.executeQuery("select leftseat from flight where Plane_Type ='" + Plane_Type[sel] +"' and Origin = '" + Origin[sel] + "'");
		while (rs.next()){
			leftseat = rs.getString("leftseat");
		}
		%>	
		
		<tr><td><%=Plane_Type[sel]%></td><td><%=Origin[sel]%></td><td><%=Destination[sel]%></td><td><%=Cost[sel] %></td><td><%=leftseat%></td>		
		</tr>				
		<%
	
		rs.close();
		stmt.close();
		conn.close();
	}
	catch (Exception e){
		out.println("Error");
		e.printStackTrace();
	}
	
	
	
	%>
	
	</table>
	<form action="Customer_Reservation.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="select" value="<%=Select%>">	
	<input type="submit" value="예약">	
	</form>	
	<form action="Customer_Cart_Delete.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="select" value="<%=Select%>">	
	<input type="submit" value="카트에서 삭제">	
	</form>	
	
</body>
</html>