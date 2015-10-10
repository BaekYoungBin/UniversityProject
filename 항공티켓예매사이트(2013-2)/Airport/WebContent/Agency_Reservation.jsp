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

	
	String Plane_Type[] = new String[10];
	String Origin[] = new String[10];
	String Destination[] = new String[10];
	String F_time[] = new String[10];
	String Lead_time[] = new String[10];
	String Cost[] = new String[10];
	String Sale[] = new String[10];
	
	try{
		DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
		Connection conn = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
		Statement stmt = conn.createStatement();
		ResultSet rs = stmt.executeQuery("select A_ID, Plane_Type, Origin, Destination, F_Time, Lead_Time from Agency_Cart where A_ID ='"+ID+"'");
		int i = 0;
		while (rs.next()){
			Plane_Type[i] = rs.getString("Plane_Type");
			Origin[i] = rs.getString("Origin");
			Destination[i] = rs.getString("Destination");
			F_time[i] = rs.getString("F_Time");
			Lead_time[i] = rs.getString("Lead_Time");
			i++;
		}
		 rs = stmt.executeQuery("insert into Agency_Reservation values(" + "'"
						+ ID + "'," + "'" + Plane_Type[sel] + "'," + "'" + Origin[sel]
						+ "', " + "'" + Destination[sel] +"'," + "'" + F_time[sel] +"'," + "'" + Lead_time[sel] +"')" );
		rs.close();
		out.print("Success!");
		%> <br> <br> 
		<form action="Agency_Reservation_View.jsp" method="POST">
		<input type="hidden" name="ID" value="<%=ID%>">
                     <input type="submit" value="예약현황 보기">
                     </form>
<form action="AgencyMain.jsp" method="POST">
<input type="hidden" name="ID" value="<%=ID%>">
<input type="submit" value="HOME">
</form>
<%

	
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