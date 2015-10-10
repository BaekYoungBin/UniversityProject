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
	String select = request.getParameter("select");	
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	int sel = Integer.valueOf(select);	

	%><form action="FlightInsert_continue.jsp" method="POST" >
	<table border='1'  bordercolor = '#AE52IC'>
	<tr>
	<th>비행기종</th><th>출발지</th><th>도착지</th><th>출발 시간</th><th>소요 시간</th><th>비용</th><th>세일</th><th>남은 좌석</th>
	</tr>
	<%
	String Plane_Type[] = new String[10];
	String Origin[] = new String[10];
	String Destination[] = new String[10];
	String F_time[] = new String[10];
	String Lead_time[] = new String[10];
	String Cost[] = new String[10];
	String Sale[] = new String[10];
	String leftseat ="null";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select Plane_Type, Origin, Destination, F_Time, Lead_Time, Cost, Sale from flight");
		int i = 0;
		while (rs.next()){
			Plane_Type[i] = rs.getString("Plane_Type");
			Origin[i] = rs.getString("Origin");
			Destination[i] = rs.getString("Destination");
			F_time[i] = rs.getString("F_Time");
			Lead_time[i] = rs.getString("Lead_Time");
			Cost[i] = rs.getString("Cost");
			Sale[i] = rs.getString("Sale");		
			i++;
		}
		rs = stmt.executeQuery("select leftseat from flight where Plane_Type ='"+Plane_Type[sel]+"'");
		while (rs.next()){
			leftseat = rs.getString("leftseat");		
		}
		%>	
		<tr><td><%=Plane_Type[sel]%></td><td><%=Origin[sel]%></td><td><%=Destination[sel]%></td><td><%=F_time[sel] %></td><td><%=Lead_time[sel]%>
		</td><td><%=Cost[sel] %></td><td><%=Sale[sel]%></td><td><%=leftseat%></td>			
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
	<h5> 주의! 수정/삭제 할 시 예약중인 고객님들에게 알리고 환불해야 합니다. </h5>
	<input type="submit" value="수정">
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="Plane_Type" value="<%=Plane_Type[sel]%>">	
	</form>	
		
	<form action="FlightDelete.jsp" method="POST" >
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="hidden" name="Plane_Type" value="<%=Plane_Type[sel]%>">	
	<input type="submit" value="삭제">		
	</form>	
	<form action="ManagerMain.jsp" method="POST">
	<input type="hidden" name="ID" value="<%=ID%>">
	<input type="submit" value="HOME">
	</form>
	<form action="Login.jsp" method="POST"> <input type="submit" value="Logout"> </form>
	









</body>
</html>