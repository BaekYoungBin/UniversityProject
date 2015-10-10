<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body><%@ page import="java.io.*"%>
	<%@ page import="java.sql.*"%>
		<%
	String ID = request.getParameter("ID");
	String select = request.getParameter("select");	
	String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
	int sel = Integer.valueOf(select);	

	
	String Plane_Type[] = new String[10];
	String Origin[] = new String[10];
	String Destination[] = new String[10];
	String F_time[] = new String[10];
	String Lead_time[] = new String[10];
	String Cost[] = new String[10];
	String Sale[] = new String[10];
	String leftseat = "null";
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select C_ID, Plane_Type, Origin, Destination, F_Time, Lead_Time from Customer_cart where C_ID ='"+ID+"'");
		int i = 0;
		while (rs.next()){
			Plane_Type[i] = rs.getString("Plane_Type");
			Origin[i] = rs.getString("Origin");
			Destination[i] = rs.getString("Destination");
			F_time[i] = rs.getString("F_Time");
			Lead_time[i] = rs.getString("Lead_Time");
			i++;
		}
		rs = stmt.executeQuery("select leftseat from flight where Plane_Type ='"+Plane_Type[sel]+"'");
		while (rs.next()){
			leftseat = rs.getString("leftseat");		
		}
		int leftseatint = Integer.valueOf(leftseat);
		leftseatint = leftseatint -1;
		String leftseatstring = String.valueOf(leftseatint);
		if(leftseatint > 0){	
			rs = stmt.executeQuery("UPDATE FLIGHT SET leftseat = '"+leftseatstring+"' where Plane_Type ='"+Plane_Type[sel]+"'");
		 rs = stmt
				.executeQuery("insert into Customer_Reservation values(" + "'"
						+ ID + "'," + "'" + Plane_Type[sel] + "'," + "'" + Origin[sel]
						+ "', " + "'" + Destination[sel] +"'," + "'" + F_time[sel] +"'," + "'" + Lead_time[sel] +"')" );
		rs.close();
		out.print("Success!");
		}
		else
		{
			out.print("Fail 남은 좌석이 없습니다.!");
			%>
			
			<input type = "button" value = "뒤로"	onclick = "history.go(-2)">
			<%
			
		
		}
		%> <br> <br> 
		<form action="Customer_Reservation_View.jsp" method="POST">
		<input type="hidden" name="ID" value="<%=ID%>">
                     <input type="submit" value="예약현황 보기">
                     </form>
	<form action="CustomerMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
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
	
</body>
</html>