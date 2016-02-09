/**
 * 
 */
package edu.ncsu.csc216.forest_system.model;

import java.awt.Color;
import java.util.Random;

/**
 * @author bradley
 * 
 */
public abstract class Organism implements Item {

	private int timeSinceLastMeal;
	private int timeSinceLastBreed;
	private boolean canActThisStep;
	private char symbol;
	private boolean alive;
	private Color color;

	private static int seed = 500;
	private static Random randomGenerator = new Random(seed);

	// protected static int direction;

	/**
	 * @param symbol
	 * @param color
	 */
	public Organism(char symbol, Color color) {

		this.symbol = symbol;
		this.color = color;
		this.alive = true;
	}

	/**
	 * @param seed
	 */
	public static void setRandomSeed(int seed) {

		randomGenerator = new Random(seed);

		// direction = randomGenerator.nextInt(4); // Limits the results to 0,
		// 1,
		// 2, 3

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see edu.ncsu.csc216.forest_system.model.Item#isAlive()
	 */
	public boolean isAlive() {

		if (alive) {

			return true;
		} else {
			return false;
		}

	}

	/**
	 * 
	 */
	public void die() {
		alive = false;

	}

	/**
	 * @return
	 */
	public boolean canAct() {
		if (canActThisStep == true) {
			return true;

		} else {
			return false;
		}

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see edu.ncsu.csc216.forest_system.model.Item#enable()
	 */
	public void enable() {
		canActThisStep = true;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see edu.ncsu.csc216.forest_system.model.Item#disable()
	 */
	public void disable() {
		canActThisStep = false;

	}

	/**
	 * @return
	 */
	public int getTimeSinceLastBreed() {
		return timeSinceLastBreed;

	}

	/**
	 * @return
	 */
	public int getTimeSinceLastMeal() {
		return timeSinceLastMeal;

	}

	/**
	 * 
	 */
	public void incrementTimeSinceLastMeal() {
		timeSinceLastMeal++;

	}

	/**
	 * 
	 */
	public void incrementTimeSinceLastBreed() {
		timeSinceLastBreed++;

	}

	protected int getDirection() {
		return randomGenerator.nextInt(4);
	}

	/**
	 * @param where
	 * @param grid
	 * @return
	 */
	public boolean breed(Cell where, Grid grid) {
		int direction = getDirection();
		boolean breed = false;

		Cell empty = grid.findFirstEmptyNeighbor(where, direction);

		if (empty != where) {
			breed = true;
			timeSinceLastBreed = 0;

		}

		return breed;

	}

	/**
	 * @param where
	 * @param grid
	 */
	public void move(Cell where, Grid grid) {
		int direction = getDirection();
		Cell empty = grid.findFirstEmptyNeighbor(where, direction);
		Item item = grid.getItemAt(where);

		if (empty != where) {

			grid.add(item, empty);

			grid.remove(where);
		}

	}

	/**
	 * @param where
	 * @param grid
	 * @return
	 */
	public boolean eat(Cell where, Grid grid) {
		int direction = getDirection();
		
		Cell prey = findAnimal(where, direction, grid);

		if (where == prey) {
			return false;
		}else{

		Item predator = grid.getItemAt(where);

		grid.remove(prey);

		grid.add(predator, prey);

		grid.remove(where);

		return true;
		}
		

	}

	/**
	 * @param position
	 * @param startDirection
	 * @param grid
	 * @return
	 */
	private Cell findAnimal(Cell position, int startDirection, Grid grid) {

		int initialDirection = startDirection;

		if (initialDirection == 0) {
			if (!grid.isEmpty(grid.dueWest(position))) {

				if (getRank(position, grid) > getRank(grid.dueWest(position),
						grid)) {
					return grid.dueWest(position);
				}

			} else if (!grid.isEmpty(grid.dueNorth(position))) {
				if (getRank(position, grid) > getRank(grid.dueNorth(position),
						grid)) {
					return grid.dueNorth(position);
				}

			} else if (!grid.isEmpty(grid.dueEast(position))) {
				if (getRank(position, grid) > getRank(grid.dueEast(position),
						grid)) {
					return grid.dueEast(position);
				}

			} else if (!grid.isEmpty(grid.dueSouth(position))) {
				if (getRank(position, grid) > getRank(grid.dueSouth(position),
						grid)) {
					return grid.dueSouth(position);
				}

			} else {
				return position;

			}

		} else if (initialDirection == 1) {
			if (!grid.isEmpty(grid.dueNorth(position))) {
				if (getRank(position, grid) > getRank(grid.dueNorth(position),
						grid)) {
					return grid.dueNorth(position);
				}

			} else if (!grid.isEmpty(grid.dueEast(position))) {
				if (getRank(position, grid) > getRank(grid.dueEast(position),
						grid)) {
					return grid.dueEast(position);
				}

			} else if (!grid.isEmpty(grid.dueSouth(position))) {
				if (getRank(position, grid) > getRank(grid.dueSouth(position),
						grid)) {
					return grid.dueSouth(position);
				}
			} else if (!grid.isEmpty(grid.dueWest(position))) {
				if (getRank(position, grid) > getRank(grid.dueWest(position),
						grid)) {
					return grid.dueWest(position);
				}

			} else {
				return position;

			}

		} else if (initialDirection == 2) {
			if (!grid.isEmpty(grid.dueEast(position))) {
				if (getRank(position, grid) > getRank(grid.dueEast(position),
						grid)) {
					return grid.dueEast(position);
				}

			} else if (!grid.isEmpty(grid.dueSouth(position))) {
				if (getRank(position, grid) > getRank(grid.dueSouth(position),
						grid)) {
					return grid.dueSouth(position);
				}

			} else if (!grid.isEmpty(grid.dueWest(position))) {
				if (getRank(position, grid) > getRank(grid.dueWest(position),
						grid)) {
					return grid.dueWest(position);
				}

			} else if (!grid.isEmpty(grid.dueNorth(position))) {
				if (getRank(position, grid) > getRank(grid.dueNorth(position),
						grid)) {
					return grid.dueNorth(position);
				}

			} else {
				return position;

			}

		} else if (initialDirection == 3) {
			if (!grid.isEmpty(grid.dueSouth(position))) {
				if (getRank(position, grid) > getRank(grid.dueSouth(position),
						grid)) {
					return grid.dueSouth(position);
				}

			} else if (!grid.isEmpty(grid.dueWest(position))) {
				if (getRank(position, grid) > getRank(grid.dueWest(position),
						grid)) {
					return grid.dueWest(position);
				}

			} else if (!grid.isEmpty(grid.dueNorth(position))) {
				if (getRank(position, grid) > getRank(grid.dueNorth(position),
						grid)) {
					return grid.dueNorth(position);
				}

			} else if (!grid.isEmpty(grid.dueEast(position))) {
				if (getRank(position, grid) > getRank(grid.dueEast(position),
						grid)) {
					return grid.dueEast(position);
				}
			} else {
				return position;

			}
			randomGenerator = new Random(seed);

		}
		return position;

	}

	/**
	 * @param position
	 * @param grid
	 * @return
	 */
	private int getRank(Cell position, Grid grid) {

		int rank = 0;

		Item item = grid.getItemAt(position);

		color = item.getColor();
		symbol = item.getSymbol();

		if (color == Color.green) {

			Organism animal = new LowAnimal(symbol);

			rank = animal.getFoodChainRank();

		} else if (color == Color.orange) {

			Organism animal = new MiddleAnimal(symbol);

			rank = animal.getFoodChainRank();
		} else {

			Organism animal = new HighAnimal(symbol);
			rank = animal.getFoodChainRank();
		}

		return rank;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see edu.ncsu.csc216.forest_system.model.Item#getSymbol()
	 */
	public char getSymbol() {
		return symbol;

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see edu.ncsu.csc216.forest_system.model.Item#getColor()
	 */
	public Color getColor() {
		return color;

	}

	/**
	 * @return
	 */
	public abstract int getFoodChainRank();

	/**
	 * @return
	 */
	public abstract Item makeNewBaby();

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * edu.ncsu.csc216.forest_system.model.Item#act(edu.ncsu.csc216.forest_system
	 * .model.Cell, edu.ncsu.csc216.forest_system.model.Grid)
	 */
	public abstract void act(Cell where, Grid grid);

	/**
	 * @param age
	 * @return
	 */
	public abstract boolean pastBreedTime(int age);

}