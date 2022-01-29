#pragma once
//#include"Image.h"

class Operation 
{
protected:
		
public:
	virtual void operator () (std::vector<Layer>& layers,int constant) = 0;
	std::string name;
	Operation(std::string name) : name(name){}
	Operation() {}
	
		// int i sluzi da primi kosrinicki zadatat ceo broj. u suprotnom je 0
		//ako operacija ne zahteva broj, bice zadata 0 radi postovanja potpisa operatora
}; 


class CompositeOperation : public Operation
{


public:
	virtual void operator () (std::vector<Layer>& layers, int constant)
	{
		int count = 0;
		std::for_each(opsInComp.begin(), opsInComp.end(), [&](std::shared_ptr<Operation> op)
			{
				
				(*op)(layers, constants[count++]);
			});
	};
	CompositeOperation(std::vector<std::shared_ptr<Operation>>& givenOps, std::vector<int>constants, std::string name) : Operation(name)
	{
		
		this->opsInComp = givenOps; this->constants = constants; 
	}
	CompositeOperation() {}
	std::vector<int>constants;
	std::vector<std::shared_ptr<Operation>> opsInComp;

};

class Grayscale : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{
		
		std::for_each(layers.begin(), layers.end(), [](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						
						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
							{
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
								{
									layer.getPixels()[i][j].toGrayscale();
								}

							}
						}
						
					}
					else 
					
					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].toGrayscale();
					}
					
				}
				
			});
		
	}
	Grayscale(std::string name) : Operation(name){}

};
class BlackAndWhite : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{


		std::for_each(layers.begin(), layers.end(), [](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{


						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
							{
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
								{
									layer.getPixels()[i][j].toBlackAndWhite();
								}

							}
						}
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].toBlackAndWhite();
					}

				}

			});
		
	}
	BlackAndWhite(std::string name) : Operation(name) {}

};
class Inverse : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{


		std::for_each(layers.begin(), layers.end(), [](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{


						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
							{
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
								{
									layer.getPixels()[i][j].inverse();
								}

							}
						}
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].inverse();
					}

				}

			});
	

	}
	Inverse(std::string name) : Operation(name) {}
	
};
class Median : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [](Layer& layer)
			{
				if (layer.getActivity())
				{
					std::vector<std::vector<Pixel>> tempPxs;
					tempPxs = layer.getPixels();

					if (layer.selectedState())
					{

						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
							{
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
								{
									if (i == 0 && j == 0)
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[0][1]);
										surroundingPixels.push_back(tempPxs[1][1]);
										surroundingPixels.push_back(tempPxs[1][0]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if (i == 0 && j == (layer.getWidth() - 1))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[0][layer.getWidth() - 2]);
										surroundingPixels.push_back(tempPxs[1][layer.getWidth() - 2]);
										surroundingPixels.push_back(tempPxs[1][layer.getWidth() - 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if (i == (layer.getHeight() - 1) && j == (layer.getWidth() - 1))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 1][layer.getWidth() - 2]);
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][layer.getWidth() - 2]);
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][layer.getWidth() - 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if (i == (layer.getHeight() - 1) && j == 0)
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 1][1]);
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][0]);
										surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if (i == 0 && (j != 0 && j != layer.getWidth() - 1))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[0][j - 1]);
										surroundingPixels.push_back(tempPxs[0][j + 1]);
										surroundingPixels.push_back(tempPxs[1][j]);
										surroundingPixels.push_back(tempPxs[1][j - 1]);
										surroundingPixels.push_back(tempPxs[1][j + 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if (((i != 0) && (i != layer.getHeight() - 1)) && (j == layer.getWidth() - 1))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[i - 1][j]);
										surroundingPixels.push_back(tempPxs[i + 1][j]);
										surroundingPixels.push_back(tempPxs[i][j - 1]);
										surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
										surroundingPixels.push_back(tempPxs[i + 1][j - 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if ((i == layer.getHeight() - 1) && (j != 0 && j != layer.getWidth() - 1))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[i][j + 1]);
										surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
										surroundingPixels.push_back(tempPxs[i - 1][j]);
										surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
										surroundingPixels.push_back(tempPxs[i][j - 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else if ((i != 0 && i != layer.getHeight() - 1) && (j == 0))
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
										surroundingPixels.push_back(tempPxs[i][j + 1]);
										surroundingPixels.push_back(tempPxs[i + 1][j + 1]);
										surroundingPixels.push_back(tempPxs[i - 1][j]);
										surroundingPixels.push_back(tempPxs[i + 1][j]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
									else
									{

										std::vector<Pixel> surroundingPixels;
										surroundingPixels.push_back(tempPxs[i - 1][j]);
										surroundingPixels.push_back(tempPxs[i + 1][j]);
										surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
										surroundingPixels.push_back(tempPxs[i][j + 1]);
										surroundingPixels.push_back(tempPxs[i][j - 1]);
										surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
										surroundingPixels.push_back(tempPxs[i + 1][j - 1]);
										surroundingPixels.push_back(tempPxs[i + 1][j + 1]);
										layer.getPixels()[i][j].median(surroundingPixels);
									}
								}

							}
						}

						
					}
					else 
					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)
							{


								if (i == 0 && j == 0)
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[0][1]);
									surroundingPixels.push_back(tempPxs[1][1]);
									surroundingPixels.push_back(tempPxs[1][0]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if (i == 0 && j == (layer.getWidth() - 1))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[0][layer.getWidth() - 2]);
									surroundingPixels.push_back(tempPxs[1][layer.getWidth() - 2]);
									surroundingPixels.push_back(tempPxs[1][layer.getWidth() - 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if (i == (layer.getHeight() - 1) && j == (layer.getWidth() - 1))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 1][layer.getWidth() - 2]);
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][layer.getWidth() - 2]);
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][layer.getWidth() - 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if (i == (layer.getHeight() - 1) && j == 0)
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 1][1]);
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][0]);
									surroundingPixels.push_back(tempPxs[layer.getHeight() - 2][1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if (i == 0 && (j != 0 && j != layer.getWidth() - 1))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[0][j - 1]);
									surroundingPixels.push_back(tempPxs[0][j + 1]);
									surroundingPixels.push_back(tempPxs[1][j]);
									surroundingPixels.push_back(tempPxs[1][j - 1]);
									surroundingPixels.push_back(tempPxs[1][j + 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if (((i != 0) && (i != layer.getHeight() - 1)) && (j == layer.getWidth() - 1))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[i - 1][j]);
									surroundingPixels.push_back(tempPxs[i + 1][j]);
									surroundingPixels.push_back(tempPxs[i][j - 1]);
									surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
									surroundingPixels.push_back(tempPxs[i + 1][j - 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if ((i == layer.getHeight() - 1) && (j != 0 && j != layer.getWidth() - 1))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[i][j + 1]);
									surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
									surroundingPixels.push_back(tempPxs[i - 1][j]);
									surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
									surroundingPixels.push_back(tempPxs[i][j - 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else if ((i != 0 && i != layer.getHeight() - 1) && (j == 0))
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
									surroundingPixels.push_back(tempPxs[i][j + 1]);
									surroundingPixels.push_back(tempPxs[i + 1][j + 1]);
									surroundingPixels.push_back(tempPxs[i - 1][j]);
									surroundingPixels.push_back(tempPxs[i + 1][j]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}
								else
								{

									std::vector<Pixel> surroundingPixels;
									surroundingPixels.push_back(tempPxs[i - 1][j]);
									surroundingPixels.push_back(tempPxs[i + 1][j]);
									surroundingPixels.push_back(tempPxs[i - 1][j + 1]);
									surroundingPixels.push_back(tempPxs[i][j + 1]);
									surroundingPixels.push_back(tempPxs[i][j - 1]);
									surroundingPixels.push_back(tempPxs[i - 1][j - 1]);
									surroundingPixels.push_back(tempPxs[i + 1][j - 1]);
									surroundingPixels.push_back(tempPxs[i + 1][j + 1]);
									layer.getPixels()[i][j].median(surroundingPixels);
								}

							}
					}

					
				
						
				}
				

				
			});

		
	}
	Median(std::string name) : Operation(name) {}
	
};
class Add : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{


		std::for_each(layers.begin(), layers.end(), [&constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
							{
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
								{
									for (int i = r.getY(); i < r.getHeight(); i++)
										for (int j = r.getX(); j < r.getWidth(); j++)
											layer.getPixels()[i][j].add(constant);
								}

							}
						}
					
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].add(constant);
					}

				}

			});


	}
	Add(std::string name) : Operation(name) {}

};
class Sub : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
											layer.getPixels()[i][j].sub(constant);
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)
								layer.getPixels()[i][j].sub(constant);
					}

				}

			});


	}
	Sub(std::string name) : Operation(name) {}
	
};
class InverseSub : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)	
											layer.getPixels()[i][j].inverseSub(constant);

					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].inverseSub(constant);
					}

				}

			});


	}
	InverseSub(std::string name) : Operation(name) {}
	
};
class Mul : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{

						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
											layer.getPixels()[i][j].mul(constant);

					
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].mul(constant);
					}

				}

			});


	}
	Mul(std::string name) : Operation(name) {}
	
};
class Div : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						for (auto r : layer.getSelection()->getRechtangles())
						{

							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].div(constant);
						}	
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].div(constant);
					}

				}

			});


	}
	Div(std::string name) : Operation(name) {}
	
};
class InverseDiv : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						for (auto r : layer.getSelection()->getRechtangles())
						{
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].inverseDiv(constant);
						}

					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].inverseDiv(constant);
					}

				}

			});


	}
	InverseDiv(std::string name) : Operation(name) {}

};
class Power : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
						

						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].power(constant);
						
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].power(constant);
					}

				}

			});


	}
	Power(std::string name) : Operation(name) {}
	
};
class Log : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{


						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].Log();
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].Log();
					}

				}

			});


	}
	Log(std::string name) : Operation(name) {}
	
};
class Min : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{

						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].min(constant);
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].min(constant);
					}

				}

			});


	}
	Min(std::string name) : Operation(name) {}

};
class Max : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{
							for (auto r : layer.getSelection()->getRechtangles())
								for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
									for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
										layer.getPixels()[i][j].max(constant);
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].max(constant);
					}

				}

			});


	}
	Max(std::string name) : Operation(name) {}

};
class Abs : public  Operation
{
public:
	void operator () (std::vector<Layer>& layers, int constant) override
	{

		std::for_each(layers.begin(), layers.end(), [constant](Layer& layer)
			{
				if (layer.getActivity())
				{
					if (layer.selectedState())
					{


						for (auto r : layer.getSelection()->getRechtangles())
							for (int i = r.getY(); i > (r.getY() - r.getHeight()) - 1; i--)
								for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
									layer.getPixels()[i][j].abs();
					}
					else

					{
						for (int i = 0; i < layer.getHeight(); i++)
							for (int j = 0; j < layer.getWidth(); j++)

								layer.getPixels()[i][j].abs();
					}

				}

			});


	}
	Abs(std::string name) : Operation(name) {}
	
};

