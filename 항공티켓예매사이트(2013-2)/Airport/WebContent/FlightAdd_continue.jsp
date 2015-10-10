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
	String Plane_type = request.getParameter("Plane_type");
	String Origin = request.getParameter("Origin");
	String Destination = request.getParameter("Destination");
	String F_time = request.getParameter("F_time");
	String Lead_time = request.getParameter("Lead_time");
	String Cost = request.getParameter("Cost");
	String Sale = request.getParameter("Sale");
	String leftseat = request.getParameter("leftseat");
%>
	<%
		int validate = 1;
		String DB_URL = "jdbc:oracle:thin:@165.132.221.101:1521:XE";
		try{
			DriverManager.registerDriver(new oracle.jdbc.driver.OracleDriver());
			Connection con = DriverManager.getConnection("jdbc:oracle:thin:@165.132.221.101:1521:XE","db09253072","ghk2xld");
			Statement stmt = con.createStatement();
		
			// validate check
			if (Plane_type.length() > 20 || Plane_type.length() < 1) {
				out.print("Too long or short Plane_tyme");
				validate = 0;
			} 
			if (Origin.length() > 20 || Origin.length() < 1) {
				out.print("Too long or short Origin");
				validate = 0;
			}
			
			if (Destination.length() > 20 || Destination.length() < 1) {
				out.print("Too long or short Destination");
				validate = 0;
			}
			if (F_time.length() > 20 || F_time.length() < 1) {
				out.print("Too long or short F_time");
				validate = 0;
			}
			if (Lead_time.length() > 20 || Lead_time.length() < 1) {
				out.print("Too long or short Lead_time");
				validate = 0;
			}
			if (Cost.length() > 4 || Cost.length() < 1) {
				out.print("Too long or short Cost");
				validate = 0;
			}
			if (Sale.length() > 2 ) {
				out.print("Too long");
				validate = 0;
			}
			if (leftseat.length() > 3){
				out.print("Too Many");
			}
			if (validate == 1) {
				ResultSet rs = stmt
						.executeQuery("insert into flight values(" + "'"
								+ Plane_type + "'," + "'" + Origin + "'," + "'" + Destination
								+ "', " + "'" + F_time +"'," + "'" + Lead_time+"'," + "'"+Cost +"',"+"'" + Sale +"', '" +leftseat +"')" );
				rs.close();
				out.print("Success!");
				%> <br> <br> <form action="ManagerFlight.jsp" method="POST">
				<input type="hidden" name="ID" value="<%=ID%>">
	                         <input type="submit" value="HOME">
	                         </form>
	 <%
			}
			else
				%> <br> <br> <input type="button" value="뒤로" onclick="history.go(-1)"> <%
			stmt.close();
			con.close();
			
			out.print("ok");
		} catch (Exception e) {
			out.println("ERROR");
			e.printStackTrace();
		}
	%>
</body>
</html>