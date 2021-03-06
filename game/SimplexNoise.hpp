#pragma once

class SimplexNoise
{
public:	
	// 2D simplex noise
	static double noise(double m_xin, double m_yin, int m_seed);

	// 3D simplex noise
	static double noise3D(double m_xin, double m_yin, double m_zin, int m_seed);

	/**
   * Gibt den Simplex-Noise-Funktionswert zurueck im Intervall [m_c,m_d] 
 	 * @param m_c Intervallanfang
 	 * @param m_d Intervallende
 	 * @param m_simpNoise Wert aus SimplexNoise im Intervall [-1,1]
 	 * @return Wert zwischen m_c und m_d 
 	 */
	static int noiseInt(int m_c, int m_d, double m_simpNoise);

private:
	// Inner class to speed up gradient computations
	// (array access is a lot slower than member access)
	class Grad {
	public:
		double m_x, m_y, m_z, m_w;
	
	public:
		Grad(double m_x, double m_y, double m_z) {
			Grad::m_x = m_x;
			Grad::m_y = m_y;
			Grad::m_z = m_z;
		}

	};

	// Method to ...
	static double dot(Grad g, double m_x, double m_y) {
		return g.m_x*m_x + g.m_y*m_y;
	};

	static double dot(Grad g, double m_x, double m_y, double m_z) {
		return g.m_x*m_x + g.m_y*m_y + g.m_z*m_z;
	};

	// This method is a *lot* faster than using (int)Math.floor(x)
	static int fastfloor(double m_x) {
		int m_xi = (int)m_x;
		if(m_x < m_xi) {
			return m_xi - 1;
		}
		else {
			return m_xi;
		}
	}
	
};